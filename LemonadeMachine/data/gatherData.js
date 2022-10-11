console.log("test");

function setValue() {
  let data = document.getElementById("MachineState");
  var req = new XMLHttpRequest();
  req.open("GET", "/api/ledStatus", false);
  req.send(null);
  if (req.status == 200) data.textContent = req.responseText;
  setTimeout("setValue();", 1000);
}

window.onload = function () {
    setValue();
};