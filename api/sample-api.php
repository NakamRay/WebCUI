<?php

header("Access-Control-Allow-Origin: *");
header("Access-Control-Allow-Headers: Content-Type, Origin, X-Requested-With");
header("Access-Control-Allow-Methods: POST, GET");
header("Content-Type: text/plain; charset=UTF-8");

// Change depending on the locale of your server
putenv("LANG=C.UTF-8");
// putenv("LANG=ja_JP.UTF-8");

$prefix = '';
$suffix = '';
$deco_start = '';
$deco_end   = '';

switch ($_POST['enable']) {
  case 'ps':
  $prefix = $_POST['prefix'];
  $suffix = $_POST['suffix'];
  break;
  case 'p':
  $prefix = $_POST['prefix'];
  break;
  case 's':
  $suffix = $_POST['suffix'];
  break;
}

if ($_POST['decoration'] == 'true') {
  if ($_POST['color'] == 'red') {
    $deco_start = '<font class="red--text">' . $deco_start;
    $deco_end   = $deco_end . '</font>';
  }
  if ($_POST['color'] == 'green') {
    $deco_start = '<font class="green--text">' . $deco_start;
    $deco_end   = $deco_end . '</font>';
  }
  if ($_POST['color'] == 'blue') {
    $deco_start = '<font class="blue--text">' . $deco_start;
    $deco_end   = $deco_end . '</font>';
  }
  if ($_POST['bold'] == 'true') {
    $deco_start = '<b>' . $deco_start;
    $deco_end   = $deco_end . '</b>';
  }
  if ($_POST['underline'] == 'true') {
    $deco_start = '<u>' . $deco_start;
    $deco_end   = $deco_end . '</u>';
  }
}

echo '* Generated Message<br>';
echo $deco_start . $prefix . $_POST['message'] . $suffix . $deco_end;

?>
