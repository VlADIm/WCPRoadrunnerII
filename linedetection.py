import cv2
import numpy as np
from matplotlib import pyplot as plt

def line_detection(img):

    minLineLength = 100
    maxLineGap = 10
    threshold = 100

    edge = cv2.Canny(img, 150,200)

    cv2.imshow("Canny Edge Result", edge)

    lines = cv2.HoughLinesP(edge, 1,np.pi/180,200,threshold, minLineLength, maxLineGap)

    cv2.imshow("Lane Detection", lines)

def main():

    images = ["straight_lane.png", "right_turn.png", "left_turn.png"]

    image = cv2.imread("right_turn.png");
    cv2.imshow("Test", image)

    value = input("press enter")
    # img = cv2.cvtColor(image, cv2.COLOR_RGB2GRAY)
    # line_detection(image)

    # for i in images:
    #
    #     image = cv2.imread(i,0);
    #     cv2.imshow("Test", image)
    #     # img = cv2.cvtColor(image, cv2.COLOR_RGB2GRAY)
    #     line_detection(image)
    #
    #
main()
