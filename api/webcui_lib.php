<?php

function getString($paramName) {
    $param = $_POST[$paramName];
    $param = escapeshellarg($param);
    return $param;
}

function getFilename($paramName) {
    $param = $_POST[$paramName];
    $param = basename($param);
    $param = escapeshellarg($param);
    return $param;
}

function getInt($paramName) {
    $param = $_POST[$paramName];
    return (int)$param;
}

function getFloat($paramName) {
    $param = $_POST[$paramName];
    return (float)$param;
}

function printLine($line) {
    echo str_replace(" ", "&nbsp;", htmlspecialchars($line, ENT_QUOTES)) . "<br>";
}

function printOutput($output) {
    for ($i = 0; $i < count($output); $i++) {
        printLine($output[$i]);
    }
}

?>
