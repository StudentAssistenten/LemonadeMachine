console.log("test");

window.onload = function () {
  let data = document.getElementById("MachineState");
  var req = new XMLHttpRequest();
  req.open("GET", "/api/ledStatus", false);
  req.send(null);
  if (req.status == 200) 
    data.textContent = req.responseText;
};
