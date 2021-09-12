<?php

header('Access-Control-Allow-Origin: *');
header('Access-Control-Allow-Headers: Content-Type, Origin, X-Requested-With');
header('Access-Control-Allow-Methods: POST, GET');
header('Content-Type: text/plain; charset=UTF-8');

// Change depending on the locale of your server
putenv('LANG=C.UTF-8');

set_time_limit(9999);

sleep(1);

exec('python3 sample-app.py "' . $_POST['text'] . '"', $opt);

echo $opt[0];

?>
