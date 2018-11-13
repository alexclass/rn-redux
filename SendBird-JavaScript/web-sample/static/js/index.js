
var userId = '';
var nickname = '';

function login(){
  if (nickname.isEmpty()) {
    alert('Please enter user nickname');
    return;
  }
  window.location.href = 'chat.html?userid=' + encodeURIComponent(userId) + '&nickname=' + encodeURIComponent(nickname);
}

$('#user_nickname').change(function() {
  userId = $('#user_id').val().trim();
  nickname = $('#user_nickname').val().trim();
});

$('#user_nickname').keydown(function(e){
  if (e.which == 13) {
    nickname = $('#user_nickname').val().trim();
    login();
  }
});

$('#btn_start').click(function() {
  login();
});

$(document).ready(function() {
  $('#user_nickname').val('');
  $('#user_nickname').focus();

  $('#user_id').val(getUserId());
});