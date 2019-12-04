import cv2
import numpy as np
from matplotlib import pyplot as plt

kernel_small = cv2.getStructuringElement(cv2.MORPH_ELLIPSE,(3,3))
kernel_medium = cv2.getStructuringElement(cv2.MORPH_ELLIPSE,(5,5))
kernel_large = cv2.getStructuringElement(cv2.MORPH_ELLIPSE,(7,7))



def testDetection(img):

    img = cv2.GaussianBlur(img,(11,11),5)

    image = cv2.cvtColor(img, cv2.COLOR_RGB2HSV)

    hsv = image.copy()
    # hsv = cv2.bilateralFilter(hsv, 9, 110, 110)

    lower = np.array([0,50,50])
    upper = np.array([180,255 - 50, 255 - 50])

    mask = cv2.inRange(hsv, lower, upper)
    res = cv2.bitwise_and(img, img, mask=mask)
    line = res.copy()

    rows,cols,channels = line.shape

    starting_x = int(cols/2)
    starting_y = rows - 1

    queue = []
    points = []

    for offset in range(int(cols/2)):
        if(line[rows-1,int(cols/2)+offset,2] != 0):
            queue.append([int(cols/2)+offset,rows-1])
            break
        elif(line[rows-1,int(cols/2)-offset,2] != 0):
            queue.append([int(cols/2)-offset,rows-1])
            break

    counter = 0
    while(counter < 500  and len(queue) > 0):
        i,j = queue.pop(0);
        points.append([i,j])
        counter += 1
        #left
        queue.append([i+1,j])
        #right
        queue.append([i-1,j])
        #up
        if(not([i,j-1] in queue or [i,j-1] in points)):
            queue.append([i,j-1])



    # for row_offset in range(res.shape[0]):
    #     for cols_offset in range(res.shape[1]);


    cv2.namedWindow("COLORS WOOOO")
    cv2.imshow("COLORS WOOOO", res)

    cv2.namedWindow("LINE WOOOO")
    cv2.imshow("LINE WOOOO", line)


def detectColoredRegions(img):

    for i in range(30,181,30):

        img = cv2.GaussianBlur(img,(11,11),5)

        image = cv2.cvtColor(img, cv2.COLOR_RGB2HSV)

        hsv = image.copy()
        # hsv = cv2.bilateralFilter(hsv, 9, 110, 110)

        lower = np.array([(i-30),70,70])
        upper = np.array([i,180,180])


        mask = cv2.inRange(hsv, lower, upper)

        res = cv2.bitwise_and(img, img, mask=mask)

        # for i in range(hsv.shape[0]):
        #     for j in range(hsv.shape[1]):
        #         # print(hsv[i,j,0])
        #         hsv[i,j,0] = 0

        cv2.namedWindow("%d" %(i))
        cv2.imshow("%d" %(i), res)


        rgb = cv2.cvtColor(hsv, cv2.COLOR_HSV2RGB)

        # binary = cv2.cvtColor(rgb, cv2.COLOR_RGB2GRAY)
        # ret, binary = cv2.threshold(binary,220,255,cv2.THRESH_BINARY_INV)


        # binary = cv2.morphologyEx(binary, cv2.MORPH_CLOSE, kernel_small, iterations = 1)
        # binary = cv2.morphologyEx(binary, cv2.MORPH_OPEN, kernel_medium, iterations = 1)

        # return rgb



def detection(img):
    # Denoising Image
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



def main():

    cap = cv2.VideoCapture(0)

    while(True):
        # Capture frame-by-frame
        ret, frame = cap.read()

        # Our operations on the frame come here
        # gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

        # image = detectColoredRegions(frame)

        image = testDetection(frame)

        # image = detection(frame)

        cv2.namedWindow("Starting")
        cv2.imshow("Starting", frame)

        # cv2.namedWindow("Binary")
        # cv2.imshow("Binary", image)

        # cv2.namedWindow("HSV")
        # cv2.imshow("HSV", rgb)


        if cv2.waitKey(1) & 0xFF == 27:
            break

    # When everything done, release the capture
    cap.release()
    cv2.destroyAllWindows()


main()
