<?php

$fp = stream_socket_client("tcp://localhost:10000", $errno, $errstr);
fwrite($fp, '{"nodeid":1000340517089,"action":0,"state":1}');
echo fread($fp, 1000);
fclose($fp);
?>
