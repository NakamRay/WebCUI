<?php

require("webcui_lib.php");

header('Access-Control-Allow-Origin: *');
header('Access-Control-Allow-Headers: Content-Type, Origin, X-Requested-With');
header('Access-Control-Allow-Methods: POST, GET');
header('Content-Type: text/plain; charset=UTF-8');

// Change depending on the locale of your server
putenv("LANG=C.UTF-8");
setlocale(LC_CTYPE, "C.UTF-8");

$prop   = getString('prop');
$hs   = $_POST['hs'];

$ip = $_SERVER['REMOTE_ADDR'];

$tmpfile = 'c' . $ip . '_' . substr(time().PHP_EOL, 0, -1) . '.hs';

$fp = fopen("./log/$tmpfile", "w");
fwrite($fp, $hs);
fclose($fp);

$timeout = 'timeout 10 ';

$cmd = "cd ../gsol/ ; stack exec gsol ../api/log/$tmpfile $prop";

exec($cmd, $output);

printOutput($output);

?>
