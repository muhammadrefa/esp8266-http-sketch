<?php

	$data = json_decode(file_get_contents("php://input"), true);
	
	$var1 = $data['var1'];
	$var2 = $data['var2'];
	
	echo "Isinya adalah <b>".$var1."</b> dan <b>".$var2."</b> (POST JSON)";

?>
