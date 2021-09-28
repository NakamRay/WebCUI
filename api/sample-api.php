<?php

header('Access-Control-Allow-Origin: *');
header('Access-Control-Allow-Headers: Content-Type, Origin, X-Requested-With');
header('Access-Control-Allow-Methods: POST, GET');
header('Content-Type: text/plain; charset=UTF-8');

// Change depending on the locale of your server
putenv('LANG=C.UTF-8');

set_time_limit(9999);

sleep(1);

$type = $_POST['type'];
$base = $_POST['base'];
$height = $_POST['height'];
$radius = $_POST['radius'];
$setPi = $_POST['setPi'];
$pi = $_POST['pi'];

if ($type == 'rect') {
    exec("python3 calc_rect.py $base $height", $opt);
} else if ($type == 'circle') {
    if ($setPi == 'false') {
        $pi = 3.14;
    }
    exec("python3 calc_circle.py $radius $pi", $opt);
}

echo $opt[0];

?>
