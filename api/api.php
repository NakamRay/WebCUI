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
$s      = $_POST['s'];
$r      = $_POST['r'];
$t      = $_POST['t'];
$n      = $_POST['n'];
$p      = $_POST['p'];
$phases = $_POST['phases'];
$hs     = $_POST['hs'];

$ip = $_SERVER['REMOTE_ADDR'];

$option = '';

if ($s == 'true') {
    $option = $option . ' -s';
}
if ($r == 'true') {
    $option = $option . ' -r';
}
if ($t == 'true') {
    $option = $option . ' -t';
}
if ($n == 'true') {
    $option = $option . ' -n';
}
if ($p == 'true') {
    $option = $option . ' -p';
}
if ($phases == 'true') {
    $option = $option . ' --phases';
}

$tmpfile = './log/c' . $ip . '_' . substr(time().PHP_EOL, 0, -1) . '.hs';

$fp = fopen("$tmpfile", "w");
fwrite($fp, $hs);
fclose($fp);

$timeout = 'timeout 10 ';

$cmd = "/home/t201d068/.local/bin/gsol $tmpfile $prop $option 2>&1";

exec($cmd, $output);

printOutput($output);

?>
