<?php

require("webcui_lib.php");

header('Access-Control-Allow-Origin: *');
header('Access-Control-Allow-Headers: Content-Type, Origin, X-Requested-With');
header('Access-Control-Allow-Methods: POST, GET');
header('Content-Type: text/plain; charset=UTF-8');

// Change depending on the locale of your server
putenv("LANG=C.UTF-8");
setlocale(LC_CTYPE, "C.UTF-8");

$rs = $_POST['rs'];
$pro = getString('pro');
$form = $_POST['form'];

$ip = $_SERVER['REMOTE_ADDR'];

$tmpfile = './sol/log/c' . $ip . '_' . substr(time().PHP_EOL, 0, -1);

if ($form == 'haskell') {
  $tmpfile = $tmpfile . '.hs';
} else {
  $tmpfile = $tmpfile . '.' . $form;
}

$fp = fopen($tmpfile, "w");
fwrite($fp, $rs);
fclose($fp);

$timeout = 'timeout 10 ';
$cmd = '';

if ($form == 'haskell' && ($pro == '\'cri\'' || $pro == '\'snG\'' || $pro == '\'cr\'')) {
  if ($pro == '\'snG\'') {
    $pro == 'sn';
  }
  $cmd = './sol/gsol-wrapper.sh ' . $pro . ' ' . $tmpfile;
} else if ($form != 'haskell') {
  if ($pro == '\'cr\'' || $pro == '\'sn\'') {
    $cmd = $timeout . './sol/Main ' . $pro . ' ' . $tmpfile . ' --sol= 2>&1';
  } else if ($pro == '\'snG\'') {
    $cmd = $timeout . './sol/Main sn ' . $tmpfile . ' --sol=GS 2>&1';
  } else {
    $cmd = 'echo "fatal error: the combination of the format and command is impossible." 2>&1';
  }
} else {
  $cmd = 'echo "fatal error: the combination of the format and command is impossible." 2>&1';
}

exec($cmd, $opt);

printOutput($output);

?>
