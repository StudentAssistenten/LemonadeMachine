console.log("test");



function feedback() // Todo: make better function
{
  alert("Uw limonade wordt gemaakt!");
}

function makeLemonadeRequest(type)
{
  var sweetness;
  if(type == 3) {
    type  = Math.floor(randomNumber(0, 3));
    sweetness = Math.floor((Math.random() * 10) + 1) / 10;
  } else {
    sweetness = document.getElementById("lemonadeSweetness".concat(type)).value;
  }
  console.log("Making lemonade request type: " + type + " sweetness: " + sweetness);
  var req = new XMLHttpRequest();
  let url = "/api/makeLemonade?lemonade=".concat(type).concat("&sweetness=").concat(sweetness);
  req.open("GET", url, false);
  req.send(null);
  if (req.status == 200) console.log(req.responseText);
  if(req.responseText == "OK")
  {
    feedback();
  }
}


function randomNumber(min, max) { 
  return Math.random() * (max - min) + min;
} 
