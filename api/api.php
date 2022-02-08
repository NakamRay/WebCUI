<?php

require("webcui_lib.php");

header('Access-Control-Allow-Origin: *');
header('Access-Control-Allow-Headers: Content-Type, Origin, X-Requested-With');
header('Access-Control-Allow-Methods: POST, GET');
header('Content-Type: text/plain; charset=UTF-8');

// Change depending on the locale of your server
putenv("LANG=C.UTF-8");
setlocale(LC_CTYPE, "C.UTF-8");

$xi = getString('xi');
$ga = getString('ga');
$term = getString('term');
$newTerm = getString('newTerm');

if ($_POST['isUntyped'] == 'true') {
    $option = '-u';
} else {
    $option = '';
}

$base = './lcii/API';

switch ($_POST['mode']) {
    case 'init':
        $cmd = "$base init $option $xi $ga $term";
        break;
    case 'red':
        $num = '"' . $_POST['num'] . '"';
        $cmd = "$base red $option $xi $ga $newTerm $num";
        break;
    case 'check':
        $cmd = "$base check $xi $ga $term";
        break;
}

exec($cmd, $outputs);

printOutput($output);

?>
