<?php

header('Access-Control-Allow-Origin: *');
header('Access-Control-Allow-Headers: Content-Type, Origin, X-Requested-With');
header('Access-Control-Allow-Methods: POST, GET');
header('Content-Type: text/plain; charset=UTF-8');

// Change depending on the locale of your server
putenv('LANG=C.UTF-8');
// putenv('LANG=ja_JP.UTF-8');

define('app', './app/genHTMLtext');
define('message', ' "' . $_POST['message'] . '"');
define('prefix', ' "' . $_POST['prefix'] . '"');
define('suffix', ' "' . $_POST['suffix'] . '"');
define('enable', ' "' . $_POST['enable'] . '"');
define('decoration', ' "' . $_POST['decoration'] . '"');
define('color', ' "' . $_POST['color'] . '"');
define('bold', ' "' . $_POST['bold'] . '"');
define('underline', ' "' . $_POST['underline'] . '"');

exec(app . message . prefix . suffix . enable . decoration . color . bold . underline, $opt);

echo $opt[0];

?>
