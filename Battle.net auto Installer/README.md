Battle.net auto installer
    Purpose:
        The purpose of this automation script is to automatatically install warzone(for now) on the battle.net installer. For context, i have a second ssd that i wanted to download games on but for some reason during download, file explorer opens and battle.net doesn't respond which pauses the download. It became annoying since i had to be on stanby when i felt like downloading the game, closing and reopening the launcher waiting for no response from the launcher. So then I thought of making a script that would do all this repetative work for me while i wasn't on my PC.
    
    Resources:
        PyAutoGui library: the back bone of the script that gives the script the ability to move the mouse and click the right buttons. Link to PyAutoGui documentation: https://pyautogui.readthedocs.io/

        subprocess library: for starting and ending battle.net executable

        time library: for putting the script on sleep to accurately go through the process of installing the application
    
    Updates:
        5/28:
            * Able to make the window terminate if not reponsive and made it open battle.net again and terminate if not responsive again.

    BugsToFix:
        5/28:
            * On loading battle.net at login it immediately stopped responding and opened file explorer.

            * When starting battle.net it doesn't reach login page but opens file explorer. Also because it said that dll wasn't there or any other error window pop up.

            * If it's done downloading it still keeps going.

            * If there's a window pop up by battle.net as a notification it will still locate the app logo but can't click it until pop up is gone.

            * If there's already an update going once main page opens it still tries to access the logo and install.

            * If file explorer opens but battle.net is still responding it's still prone to error since clicking the pause download button makes it unresponsive.

