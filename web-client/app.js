/*jshint esversion:6*/

function postControlData(ctrlObj) {
  let settings = {
    method: 'PUT',
    url: 'http://50-81-20-64-client.mchsi.com',
    data: ctrlObj
  };
  $.ajax(settings);
}

$(function main() {

  let ctrlObj = {
    turnLeft: true //false means turn right
  };

  $('#left').on('submit',function(event) {
    postControlData(ctrlObj);
  });

});
