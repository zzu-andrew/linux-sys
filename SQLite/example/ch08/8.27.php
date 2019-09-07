<?php
$dbh = new PDO("sqlite:foods.db");
$sql = 'select * from foods where type_id=? And name=?';
$stmt = $dbh->prepare($sql);
$type_id = 9;
$name = 'JujyFruit';
$stmt->bindParam(1, $type_id, PDO_PARAM_INT);
$stmt->bindParam(1, $name, PDO_PARAM_STR, 50);
$stmt->execute();
?>
