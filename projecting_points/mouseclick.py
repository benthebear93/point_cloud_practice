import cv2
import numpy as np

class Pc2Img:
    def __init__(self):
        self._img = 0

    def mouse_event_handle(self, event, x,y,flags, param):
        img = param[0]
        if event==cv2.EVENT_LBUTTONDBLCLK:
            cv2.circle(img, (x, y), 10, (255, 0, 0), -1)
            cv2.imshow("Pc2Img", img)

    def make_img(self):
        print("make img")
        img = np.zeros((300, 300, 1), np.uint8) # y , x
        cv2.namedWindow('Pc2Img')
        cv2.setMouseCallback('Pc2Img', self.mouse_event_handle, param = [img])
        while True:
            cv2.imshow('Pc2Img', img)
            if cv2.waitKey(20) & 0xFF == 27:
                break   
        cv2.destroyAllWindows()

if __name__=="__main__":
    print("start")
    test = Pc2Img()
    test.make_img()