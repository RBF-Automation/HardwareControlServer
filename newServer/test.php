<?php

$fp = stream_socket_client("tcp://localhost:30000", $errno, $errstr);
fwrite($fp, "Testasdfasdfasdfsing 123!");
echo fread($fp, 1000);
fclose($fp);
?>
