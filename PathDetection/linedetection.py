import cv2
import numpy as np
from matplotlib import pyplot as plt


def line_detection(img):

    image = cv2.imread(img);

    # cv2.imshow("Test", image)
    image_grey = cv2.cvtColor(image, cv2.COLOR_RGB2GRAY)

    edge = cv2.Canny(image_grey, 150,200,apertureSize = 7)
    kernel = np.ones((5,5),np.uint8)
    dilation = cv2.dilate(edge,kernel,iterations = 1)
    closing = cv2.morphologyEx(dilation, cv2.MORPH_CLOSE, kernel)
    opening = cv2.morphologyEx(closing, cv2.MORPH_OPEN, kernel)
    final = cv2.erode(opening, kernel, iterations = 1)
    cv2.namedWindow("Canny Edge Result for %s" %(img))
    cv2.imshow("Canny Edge Result for %s" %(img), final)
    minLineLength = 50
    maxLineGap = 10
    threshold =500

    lines = cv2.HoughLinesP(final, 1,np.pi/180,100,threshold, minLineLength, maxLineGap)



    if(type(lines) == np.ndarray):
        counter = 0
        for i in lines:
            for x0,y0,x1,y1 in i:
                cv2.line(image,(x0,y0),(x1,y1),(0,0,255),2)
                counter+=1

        print(counter)
    cv2.namedWindow("Lane Detection for %s" %(img))
    cv2.imshow("Lane Detection for %s" %(img), image)

def main():

    images = ["straight_line.png", "right_turn.png", "left_turn.png"]

    for i in images:
        # print("FOR IMAGE: %s" %(i))
        line_detection(i)

    cv2.waitKey(0)
main()
