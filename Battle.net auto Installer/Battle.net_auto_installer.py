import pyautogui as pag
import subprocess
import time
import sys
#import os
#drive = 'Y:'
# directory = 'Battle.net'
# filename = 'Battle.net Launcher.exe'

# Construct the full path using os.path.join()
# full_path = os.path.join(drive, directory, filename) add full path too popen

def locate_update(c):
    try:
        x,y = pag.locateCenterOnScreen('C://Users//migno//OneDrive//Desktop//auto_images//update.jpg', confidence=c)
        print(x,y)
        pag.click(x,y)
        print("clicked update")
    except pag.ImageNotFoundException:   
        print("couldn't find")

def locate_install(c):
    try:
        x,y = pag.locateCenterOnScreen('C://Users//migno//OneDrive//Desktop//auto_images//install_image.jpg', confidence=c)
        print(x,y)
        pag.click(x,y)
        print("clicked install")
    except pag.ImageNotFoundException:   
        print("couldn't find")

def locate_continue(c):
    try:
        x,y = pag.locateCenterOnScreen('C://Users//migno//OneDrive//Desktop//auto_images//continue_image.jpg', confidence=c)
        print(x,y)
        pag.click(x,y)
        print("clicked continue")
    except pag.ImageNotFoundException:
        print("couldn't find")

def locate_checkbox(c):
    try:
        x,y = pag.locateCenterOnScreen('C://Users//migno//OneDrive//Desktop//auto_images//mw2_checkbox.jpg', confidence=c)
        print(x,y)
        pag.click(x,y)
        print("checkbox")
    except pag.ImageNotFoundException:
        print("couldn't find")

def locate_start_install(c):
    try:
        x,y = pag.locateCenterOnScreen('C://Users//migno//OneDrive//Desktop//auto_images//start_install.jpg', confidence=c)
        print(x,y)
        pag.click(x,y)
        print("clicked start")
    except pag.ImageNotFoundException:
        print("couldn't find")

def test_func(c):
    try:
        x,y = pag.locateCenterOnScreen('C://Users//migno//OneDrive//Desktop//auto_images//test.jpg', confidence=c)
        print(x,y, c)
        time.sleep(0.5)
        pag.moveTo(x,y)
    except pag.ImageNotFoundException:
        print('couldnt find the x')

def battle_net():
    temp=0
    while temp<10:
        #open battle.net
        process=subprocess.Popen('Y://Battle.net//Battle.net Launcher.exe')
        pag.FAILSAFE = True

        #wait until main window appears
        #add a case that the main window does open in which still at login waiting for password or busy queue or bad load up
        c = 0.9
        counter = 0
        #1 indicates install and 2 indicates update
        threshold = 0.4
        while True:
            try:
                x,y = pag.locateCenterOnScreen('C://Users//migno//OneDrive//Desktop//auto_images//test.jpg', confidence=c)
                print(x,y, c)
                #find the cod icon and click it
                time.sleep(0.5)
                pag.click(x,y)
                print("what's new popped up")
            except pag.ImageNotFoundException:
                try:
                    x,y = pag.locateCenterOnScreen('C://Users//migno//OneDrive//Desktop//auto_images//cod_image.png', confidence=c)
                    print(x,y, c)
                    #find the cod icon and click it
                    time.sleep(0.5)
                    pag.click(x,y)
                    print("clicked cod")
                    counter = 1
                    break
                except pag.ImageNotFoundException:
                    try:
                        x,y = pag.locateCenterOnScreen('C://Users//migno//OneDrive//Desktop//auto_images//cod_upd.jpg', confidence=c)
                        print(x,y, c)
                        time.sleep(0.5)
                        pag.moveTo(x,y)
                        counter = 2
                        break
                    except pag.ImageNotFoundException:
                        try:
                            time.sleep(0.5)
                            x,y = pag.locateCenterOnScreen('C://Users//migno//OneDrive//Desktop//auto_images//file_e.jpg', confidence=c)
                            pag.click(x,y)
                            print(x,y, c)
                            while True:
                                try:
                                    x,y = pag.locateCenterOnScreen('C://Users//migno//OneDrive//Desktop//auto_images//file_e.jpg', confidence=c)
                                    pag.click(x,y)
                                    print(x,y, c)
                                except pag.ImageNotFoundException:
                                    break
                            counter = 3
                            break
                        except pag.ImageNotFoundException:
                            print('sleep')
                            time.sleep(1)
                            print('wake up')

        #PROBLEM:might need to give time between clicks because it clicked but didn't pull cod window
        time.sleep(0.5)

        if(counter == 1):
            #if there's install button press it else if there's pause button press it (maybe keep checking for it)
            locate_install(c)
            
            #PROBLEM:needs time between install and continue
            time.sleep(0.5)

            #continue
            locate_continue(c)

            #checkboxes
            locate_checkbox(c)

            #hit start install
            locate_start_install(c)
        elif(counter == 2):
            locate_update(c)
        elif(counter == 3):
            #maybe terminate
            return 1
        #wait until either it's done or not responding
        #add a chewck for file_e and keep deleting those then if there's still not battle.net responding then press pause button then wait again for not responding
        test_func(c)
        while True:
            try:
                pag.locateCenterOnScreen('C://Users//migno//OneDrive//Desktop//auto_images//a.jpg', confidence=c)
                process.terminate()
                print("not respond")
                break
            except pag.ImageNotFoundException:
                print("couldn't find")
                time.sleep(5)
        print("done")
        temp+=1
        print(temp)  

def main():
    if len(sys.argv) > 1 or len(sys.argv) < 1:
        print("not valid input")
        exit(1)
    if(sys.argv[0] == "battle.net"):
        battle_net()
if __name__ == "__main__":
    main()