<?php

header("Access-Control-Allow-Origin: *");
header("Access-Control-Allow-Headers: Content-Type, Origin, X-Requested-With");
header("Access-Control-Allow-Methods: POST, GET");
header("Content-Type: text/plain; charset=UTF-8");

// linuxのlocaleによって変える
putenv("LANG=C.UTF-8");
// putenv("LANG=ja_JP.UTF-8");

define('app', 'eval.py');
define('formula', '"' . $_POST['formula'] . '"');

exec('python3 ' . app . ' ' . formula, $opt);

echo $opt[0];
?>