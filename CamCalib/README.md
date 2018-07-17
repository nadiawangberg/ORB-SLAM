#Camera calibration
## OpenCV calibrateCamera
We used this method to calibrate our cameras.
Link to guide: https://docs.opencv.org/3.3.1/d4/d94/tutorial_camera_calibration.html
We had two cameras, where one did not work as direct input for the calibration program. 
We therefore took a lot (100+) of pictures and used image list calibration mode. It seems there is nothing wrong with having too many pictures.
For our second camera I set Input_Delay to 5000, to have enough time to move the camera around between pictures.

One can experiment with different settings to achieve lower reprojection error. The more parameters you are trying to optimize, the higher the 
reprojection error usually gets.
camera_calibration.cpp is copied from the repository linked by the guide. 
Direct link: https://github.com/opencv/opencv/blob/master/samples/cpp/tutorial_code/calib3d/camera_calibration/camera_calibration.cpp

###Building executable file:
g++ camera_calibration.cpp -o camera_calibration `pkg-config --cflags --libs opencv`

###Running executable file:
./camera_calibration
See comments in default.xml for explanation of different calibration settings.

###Required files:
Input settings: default is default.xml
Output estimated parameters: default is out_camera_data.xml
List of pictures used for calibration: default is list_of_pictures.xml (Optional, if pictures are used for calibration)

##Generating list_of_pictures
The script writing_to_file.py can be run from command line to fill list_of_pictures.xml with paths to pictures,
provided they are located in pictures_for_calibration/ and named XXXXXX.png, where the X's make up a six digit integer
from 000000 to 999999.


##Lab notes guidance
https://www.uio.no/studier/emner/matnat/its/UNIK4690/v18/labs/lab_05/lab_5_pose_estimation_and_augmented_reality.pdf

##Camera calibration parameters
Stored in .yaml-files in folder calib_param_files. Microsoft_B means Microsoft Camera with black tape.

##Alternative method for calibrating camera
Documentation: https://docs.opencv.org/3.3.1/d7/d21/tutorial_interactive_calibration.html
NOTE: We did not get working results with this method. Provided as an alternative, in case the previous option does not work.
OpenCV interactive camera calibration application:
Calibrate camera with live feed from camera while moving it over a chess board.
Run this line in terminal, while in directory containing calibSettings.xml:
opencv_interactive-calibration -ci=1 -t=chessboard -sz=22 -w=9 -h=6 –pf=calibSettings.xml
