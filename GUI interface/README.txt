det her er hvis jeg ikke er til stede og nyt kode skal ligges på RPI. 
det er ikke muligt at bruge ssh da den er kodet op til min telefon. 

der bruges scp til at sende filer over. begge .py filer skal sendes via scp og personligt sender jeg dem en af gangen 

der er en lille chance for at pien IP adresse er ændre og hvis den er så kig på bootup når det er. 
Den viser sin IP adresse kort og den skal bruges til overførsel

sådan fungere det. 

åben CMD terminal på computer ha begge .py filer liggende lokalt og kend directory til dem 

i terminal skriver man 
scp "C:\universitet\visual studio code folder\studio codes 3 semester del2\project\repo\Projekt-3\GUI interface\program.py" peter@192.168.37.11:/home/peter/Documents/beerGame
scp "C:\universitet\visual studio code folder\studio codes 3 semester del2\project\repo\Projekt-3\GUI interface\UART.py" peter@192.168.37.11:/home/peter/Documents/beerGame

selve C:\universitet\visual studio code folder\studio codes 3 semester del2\project\repo\Projekt-3\GUI interface\UART.py skiftes ud med din directory til filens lokalisering.

koden som den spørg om er "peter1" og så tryk enter. Det burde være det. hvis ip ændre er det som regl kun de sidste 2 tal. 