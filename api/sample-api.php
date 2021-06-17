<?php

header("Access-Control-Allow-Origin: *");
header("Access-Control-Allow-Headers: Content-Type, Origin, X-Requested-With");
header("Access-Control-Allow-Methods: POST, GET");
header("Content-Type: text/plain; charset=UTF-8");

// Change depending on the locale of your server
putenv("LANG=C.UTF-8");
// putenv("LANG=ja_JP.UTF-8");

echo 'Receive: ' . $_POST['message'];

?>