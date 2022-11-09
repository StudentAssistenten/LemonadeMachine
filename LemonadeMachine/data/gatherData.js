console.log("test");

function setValues() {
  console.log("Getting values");
  // setValue("machineState");
  console.log("Setting values");
}

function feedback() // Todo: make better function
{
  alert("Uw limonade wordt gemaakt!");
}

function setValue(valueName) {
  let data = document.getElementById(valueName);
  var req = new XMLHttpRequest();
  let url = "/api/".concat(valueName);
  req.open("GET", url, false);
  req.send(null);
  if (req.status == 200) data.textContent = req.responseText;
}

function makeLemonadeRequest(type)
{
  var req = new XMLHttpRequest();
  let url = "/api/makeLemonade?lemonade=".concat(type);
  req.open("GET", url, false);
  req.send(null);
  if (req.status == 200) console.log(req.responseText);
  if(req.responseText == "OK")
  {
    feedback();
  }
}

window.onload = function () {
  setValues();
};
