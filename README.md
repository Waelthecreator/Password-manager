# Password-manager
creates strong passwords, and if User indicates that the user wants a login manager, then the program will create a login manager. the login manager will be able to add, find, delete, change, and print logins. once the user is done, the program will ask if the user wants the logins printed to a file, which can then be encrypted and decrypted using the command line. 
future upgrades:

1. enable the encrypt decrypt features.
2. create a socket local host web server which takes in POST requests.
3. create a chrome extension which can connect to said web server, which if given the correct pin using the POST request, autofills the login credentials.
4.create a GUI so it is more user friendly.


Version 2.0:
the program now incrypts and decrypts file, current program usages is: <exe> | <exe> -decrypt <filename> | <exe> -read <filename>. the first usage is for first time use or for creatings new password managers. the second usage is for decrypting the password and manager and for adding/removing logins. the third usage is for reading a file and adding/removing loings from the file.
  
  future upgrades:
  1.socket local host web server takes in POST requests.
  2. chrome extension in javascript which sends in the post requets in question
  4. creating a GUI 
