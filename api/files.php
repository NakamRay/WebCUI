<?php

header('Access-Control-Allow-Origin: *');
header('Access-Control-Allow-Headers: Content-Type, Origin, X-Requested-With');
header('Access-Control-Allow-Methods: POST, GET');
header('Content-Type: text/plain; charset=UTF-8');

putenv('LANG=C.UTF-8');

if ($_POST['path'] == null) {
  $dirs = array(
    array(
      'name' => 'hs',
      'display' => 'examples',
      'dir' => '/home/t201d068/gsol/examples'
    )
  );

  function getFiles($arr) {
    $arr['files'] = glob($arr['dir'] . '/*.hs');
    return $arr;
  }

  $files = array_map('getFiles', $dirs);
  $json = json_encode($files);
  echo $json;
  
} else {
  readfile($_POST['path']);
}

?>
