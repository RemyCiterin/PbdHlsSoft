import cv2 as cv
from itertools import chain
import socket

def main():
    webcam = cv.VideoCapture(0)
    if not webcam.isOpened():
        print("Cannot open camera")
        return -1

    UDP_IP = "192.168.1.43"
    UDP_PORT = 17014

    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    while True:
        ret, frame = webcam.read()

        if not ret:
            print("Can't receive frame")
            webcam.release()
            return -2

        gray_disp = cv.cvtColor(frame, cv.COLOR_RGB2GRAY)
        ret, gray_disp = cv.threshold(gray_disp, 127, 255, cv.THRESH_BINARY)

        gray_sent = cv.resize(gray_disp, (40, 30))
        ret, gray_sent = cv.threshold(gray_sent, 127, 1, cv.THRESH_BINARY)

        gray_sent = gray_sent[0:29, 0:29]

        arr = gray_sent.data.tolist()

        arr_1d = list(chain.from_iterable(arr))

        arr_bytes = bytes(arr_1d)

        cv.imshow("frame", gray_disp)
        if cv.waitKey(1) == ord("q"):
            break

        sock.sendto(arr_bytes, (UDP_IP, UDP_PORT))

if __name__ == "__main__":
    main()
