# Farthest-Distance-From-Indiana-Police-Stations
The algorithm is stupid because I'm bad at coding, but basically I have an array of points across Indiana and it just draws a circle around each police station and sees if there are any points not inside of the circles. If there are any points not inside of the circles it will make the circles bigger and if all the points are inside of the circles it will make the circles smaller. The radius of the circles after a bunch of iterations is the farthest distance.

Also the array of points is scuffed because the Indiana border line on the south side of the state is blad, so it leaves out little pockets on the south side. This is what the point map looks like visually: ![Indiana Point Map](indiana-point-map.jpg)

Police station locations source: https://koordinates.com/layer/108466-indiana-police-stations/data/

I used the Geocode google sheets plugin to convert the addresses to earth coordinates. Link to the plugin: https://workspace.google.com/marketplace/app/geocode_by_awesome_table/904124517349
