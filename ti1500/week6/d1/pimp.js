
// enlarge the input text
function makeTextBigger(event) {
  var size = $("text").getStyle("font-size");
  $("text").setStyle({fontSize: parseInt(size) * 1.5 + "px"});
}

// add some fancy style to the input text
function blingText(event) {
  if(this.checked) {
    $("text").addClassName("bling");
  }
  else {
    $("text").removeClassName("bling");
  }
}

// add -izzle after every sentence ended with a dot
function snoopifyText(event) {
  var text = $("text").value;
  parts = text.split(".");
  var new_text = parts.join("-izzle.");
  $("text").setValue(new_text);
}

window.onload = function() {
  $("big").observe("click", makeTextBigger);
  $("bling").observe("click", blingText);
  $("snoop").observe("click", snoopifyText);
}



