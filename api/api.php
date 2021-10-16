<?php

header('Access-Control-Allow-Origin: *');
header('Access-Control-Allow-Headers: Content-Type, Origin, X-Requested-With');
header('Access-Control-Allow-Methods: POST, GET');
header('Content-Type: text/plain; charset=UTF-8');

// Change depending on the locale of your server
putenv('LANG=C.UTF-8');

set_time_limit(9999);

$user = $_POST['user'];
$option = $_POST['option'];
$name = $_POST['name'];
$url = $_POST['url'];
$weekly = $_POST['weekly'];
$day = $_POST['day'];
$year = $_POST['year'];
$date = $_POST['date'];
$shour = $_POST['shour'];
$sminute = $_POST['sminute'];
$ehour = $_POST['ehour'];
$eminute = $_POST['eminute'];

$cmd = "./start-zoom-cui -u $user";

switch ($option) {
    case 'register':
        $cmd = "$cmd -r";
        break;
    case 'start':
        $cmd = "$cmd -s";
        break;
    case 'make':
        $stime = $shour . $sminute . '00';
        $etime = $ehour . $eminute . '00';
        $cmd = "$cmd -m --name $name --url $url --stime $stime --etime $etime";
        if ($weekly == 'true') {
            $cmd = "$cmd --weekly --day $day";
        } else {
            $cmd = "$cmd --date $year$date";
        }
        break;
    case 'list':
        $cmd = "$cmd -l";
        break;
    case 'edit':
        $stime = $shour . $sminute . '00';
        $etime = $ehour . $eminute . '00';
        $cmd = "$cmd -e --name $name --url $url --stime $stime --etime $etime";
        if ($weekly == 'true') {
            $cmd = "$cmd --weekly --day $day";
        } else {
            $cmd = "$cmd --date $year$date";
        }
        break;
    case 'delete':
        $cmd = "$cmd -d --name $name";
        break;
}

exec($cmd, $output);

for ($i=0; $i<count($output); $i++) {
    echo preg_replace('/https?:\/\/[\w\/:%#\$&\?\(\)~\.=\+\-]+/', '<a href="$0">$0</a>', $output[$i]) . '<br>';
}

?>
