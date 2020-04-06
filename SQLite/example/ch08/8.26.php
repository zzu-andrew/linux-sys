<?php

try {
  $dbh = new PDO("sqlite:foods.db");
} catch (PDOException $e) {
  echo 'Connection failed: ' . $e->getMessage();
}

$dbh->beginTransaction();
$sql = 'select * from foods limit 10';
foreach ($dbh->query($sql) as $row) {
  print $row['type_id'] . " ";
  print $row['name']    . "<br>";
}

$dressing = $dbh->quote("Newman's Own Vinegarette");
$dbh->exec("insert into foods values (NULL, 4, $dressing)");
echo $dbh->lastInsertId();
$dbh->rollback();
?>
