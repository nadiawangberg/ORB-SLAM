import argparse
import string

parser = argparse.ArgumentParser(description='Set number of pictures to use for calibration')
parser.add_argument('--total', dest='n', type=int, help='total number of pictures in directory')
parser.add_argument('--inc', dest='inc', default=1,type=int, help='increment (for many pictures). Default is 1.')
parser.add_argument('--dir', dest='directory', default='/home/havaa/camera_calibration_ws/pictures_for_calibration/', type=str, help='full path to location of pictures to use for calibration')

args = parser.parse_args()
n = args.n
inc = args.inc
directory = args.directory

#Writing to file
file_object = open("list_of_pictures.xml", "w")

file_object.write("<?xml version=\"1.0\"?>\n")
file_object.write("<opencv_storage>\n")
file_object.write("<images>\n")

for i in range(0, n, inc):
	
	print ("Writing" + directory + format(i, '06d') + ".png")
	file_object.write(directory + format(i, '06d') + ".png\n") 

file_object.write("</images>\n")
file_object.write("</opencv_storage>\n")


file_object.close()
