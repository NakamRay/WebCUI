<?php

require("webcui_lib.php");

header('Access-Control-Allow-Origin: *');
header('Access-Control-Allow-Headers: Content-Type, Origin, X-Requested-With');
header('Access-Control-Allow-Methods: POST, GET');
header('Content-Type: text/plain; charset=UTF-8');

// Change depending on the locale of your server
putenv("LANG=C.UTF-8");
setlocale(LC_CTYPE, "C.UTF-8");

$from   = getString('from');
$to     = getString('to');

$cmd = "./route $from $to";

exec($cmd, $output);

printOutput($output);

?>
