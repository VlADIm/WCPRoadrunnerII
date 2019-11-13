import cv2
import numpy as np
from matplotlib import pyplot as plt

kernel_small = cv2.getStructuringElement(cv2.MORPH_ELLIPSE,(3,3))
kernel_medium = cv2.getStructuringElement(cv2.MORPH_ELLIPSE,(5,5))
kernel_large = cv2.getStructuringElement(cv2.MORPH_ELLIPSE,(7,7))


def detection(img):

    # img = cv2.fastNlMeansDenoisingColored(img,None,10,10,7,15)

    # Existing blur
    # img = cv2.GaussianBlur(img,(7,7),1.4)

    img = cv2.GaussianBlur(img,(11,11),5)

    image = cv2.cvtColor(img, cv2.COLOR_RGB2HSV)


    hsv = image.copy()
    # hsv = cv2.bilateralFilter(hsv, 9, 110, 110)

    hsv[:,:,0] = hsv[:,:,0] - (hsv[:,:,0] % 20)
    # hsv[:,:,1] = 100
    hsv[:,:,2] = 255
    rgb = cv2.cvtColor(hsv, cv2.COLOR_HSV2RGB)
    binary = cv2.cvtColor(rgb, cv2.COLOR_RGB2GRAY)
    ret, binary = cv2.threshold(binary,220,255,cv2.THRESH_BINARY_INV)


    binary = cv2.morphologyEx(binary, cv2.MORPH_CLOSE, kernel_small, iterations = 1)
    binary = cv2.morphologyEx(binary, cv2.MORPH_OPEN, kernel_medium, iterations = 1)

    # return rgb
    return binary

def line_detection(img):

    original = cv2.imread(img);

    image = cv2.cvtColor(original, cv2.COLOR_RGB2HSV)

    hsv = image.copy()

    # hsv = cv2.bilateralFilter(hsv, 9, 75, 75)

    # hsv[:,:,0] = 0
    # hsv[:,:,1] = 0

    hsv[:,:,2] = 255

    # hsv	= cv2.ximgproc.thinning(hsv)
    # hsv[]

    # print(hsv[:])

    rgb = cv2.cvtColor(hsv, cv2.COLOR_HSV2RGB)



    binary = cv2.cvtColor(rgb, cv2.COLOR_RGB2GRAY)
    ret, binary = cv2.threshold(binary,200,255,cv2.THRESH_BINARY_INV)


    cv2.namedWindow("%s" %(img))
    cv2.imshow("%s" %(img), original)

    cv2.namedWindow("HSV Color Space for %s" %(img))
    cv2.imshow("HSV Color Space for %s" %(img), image)

    cv2.namedWindow("Color Segmentation for %s" %(img))
    cv2.imshow("Color Segmentation for %s" %(img), rgb)

    cv2.namedWindow("Binary for %s" %(img))
    cv2.imshow("Binary for %s" %(img), binary)


def test():

    images = ["warehouseimage0.jpg", "warehouseimage1.jpg", "warehouseimage2.jpg"]

    for i in images:
        line_detection(i)
    cv2.waitKey(0)

def main():
    #run test cases
    # test()


    cap = cv2.VideoCapture(0)

    while(True):
        # Capture frame-by-frame
        ret, frame = cap.read()

        # Our operations on the frame come here
        # gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

        image = detection(frame)

        # Display the resulting frame
        # cv2.imshow('frame', image)

        cv2.namedWindow("Starting")
        cv2.imshow("Starting", frame)

        cv2.namedWindow("Binary")
        cv2.imshow("Binary", image)

        # cv2.namedWindow("HSV")
        # cv2.imshow("HSV", rgb)




        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

    # When everything done, release the capture
    cap.release()
    cv2.destroyAllWindows()


main()
