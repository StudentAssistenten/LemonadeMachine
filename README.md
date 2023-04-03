# LemonadeMachine
ESP32 LemonadeMachine

Dit project wordt via platform IO op een ESP32 gezet. Eerst moeten de html files op de ESP gezet worden. Dit kan ook via platformIO. Er moet geklik worden op Upload Filesystem Image OTA. Er wordt op de website gebruik gemaakt van images van de carvan cervitan site. Hiervoor is het belangrijk dat het WiFI netwerk waar de ESP meer verbind daarwerkelijk internet heeft. Een mobiele hotspot kan hier goed voor gebruikt worden.

De image bij "2 smaken" en "random smaak" is een zelfgemaakte image. Hiervoor is een link gebruik die overtijd verloop. De foto moet opnieuw geupload worden en dan kan deze link gebruikt worden. De betreffende foto staat in de Repo.

# Setup
1. Pas in de code de inlog gegvens aan naar je eigen hotspot(WiFiSetup.h)
2. Pas in de website de plaatjes van de random en 2 smaken aan naar een werkende link. (index.html)
3. Upload de html files naar de ESP (Upload FIlesystem Image)
4. Upload de code naar de ESP
5. Haal de USB uit de esp
6. Sluit de PCB aan op 9 volt
7. Wacht tot de ESP verbinding heeft (zie LED kleuren)
8. Verbind een laptop met dezelfde hotspot als die de ESP gebruikt.
9. Ga naar het IP van de ESP voor de limonade machine website.

# Gebruik
Het is belangrijk dat er altijd een mok op de weegschaal staat. De buisjes hebben last van druk verlies waardoor deze soms leeglopen.
1. Verbind met de website van de limonade machine via een laptop
2. Zet een beker op de weegschaal en haal de lekmok weg
3. Klik nu op de gewenste limonade
4. Verwissel de beker weer terug voor de lekmok

# LED kleuren

De LED op de limoande machine laat de status zien.

Bij het verbinden knipperd de onboard led en is het RGB ledje **rood**.

Als er verbinding is gaat de onboard LED aan een is het RGB lampje **groen**.

Als er siroop in de beker gedaan wordt is het ledje **Wit**.

Als er water in de beker gedaan wordt is het ledje **blauw**.

Als de machine weer gaat wachten op een nieuw verzoek is het ledje **groen**

# Debugging
Indien er meer info nodig is om fouten te ontdekken kan er Seriele communicatie gestart worden met de ESP. Dit gaat op 115200 baud. Als er live debugging moet komen moet DEBUG_LEMONADE gedefined worden in de code.

# Schoonmaak
Er is een functie in de website van de limoande machine voor het besturen van de pompjes. Hier kunnen de pompjes 1 voor 1 aangestuud worden. Op deze manier zijn de pompjes door te spoelen met warm water.

# Issues
Als de verbinding met de hotspot wegvalt wordt deze niet opnieuw opgestart. Hiervoor moet de ESP gereset worden, het kan voorkomen dat deze 2 keer gereset moet worden om weer verbinding te maken. Verbinding maken hoor niet langer te duren dan 30 seconde. Als er na deze tijd geen verbinding is gemaakt moet de ESP gereset worden.
