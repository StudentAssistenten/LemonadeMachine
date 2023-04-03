console.log("test");



function feedback() // Todo: make better function
{
  alert("Uw limonade wordt gemaakt!");
}

function makeLemonadeRequest(type, amountOfFlavours, type2)
{
  var sweetness;
  if(type == 3) {
    type  = Math.floor(randomNumber(0, 3));
    sweetness = Math.floor((Math.random() * 10) + 1) / 10;
  } else {
    sweetness = document.getElementById("lemonadeSweetness".concat(type)).value;
  }
  var req = new XMLHttpRequest();
  var url;
  if(amountOfFlavours == 1){
    url = "/api/makeLemonade?lemonade=".concat(type).concat("&sweetness=").concat(sweetness);
    console.log("Making lemonade request type: " + type + " sweetness: " + sweetness);
  } else {
    url = "/api/makeLemonade?lemonade=".concat(type).concat("&secondFlavour=").concat(type2);
    console.log("Making lemonade request type: " + type + " sweetness: " + sweetness + " second flavour: " + type2);
  }
  console.log("URL: " + url);
  req.open("GET", url, false);
  req.send(null);
  console.log("Send request");
  if (req.status == 200) console.log(req.responseText);
  if(req.responseText == "OK")
  {
    feedback();
  }
}

function makeMixRequest()
{
  var firstflavour = document.getElementById("firstFlavour").value;
  var secondflavour = document.getElementById("secondFlavour").value;
  console.log("Making mix request first flavour: " + firstflavour + " second flavour: " + secondflavour);
  makeLemonadeRequest(Number(firstflavour), 2, Number(secondflavour));
}


function randomNumber(min, max) { 
  return Math.random() * (max - min) + min;
} 
