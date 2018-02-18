<?php
{
  //$Header: /cvsroot/tsheet/timesheet.php/mysql.db.inc,v 1.3 2005/04/17 12:19:31 vexil Exp $
  //To port to another database, simply keep this interface and duplicate the functionality.
  //Should have plug in compatibility.
  
  function dbConnect() {  		
    $GLOBALS["CONNECTED_MYSQL_DB_INC"] = 1;
    global $DATABASE_HOST, $DATABASE_USER, $DATABASE_PASS, $DATABASE_DB;
    $dbconn = new mysqli("$DATABASE_HOST","$DATABASE_USER","$DATABASE_PASS","$DATABASE_DB");

    $dbconn->select_db("$DATABASE_DB");

    $GLOBALS["dbconn"] = $dbconn;

    //$dbh = mysqli_connect("$DATABASE_HOST","$DATABASE_USER","$DATABASE_PASS") or die("Unable to connect to SQL server: ". mysql_error());
    //$dbh->mysqli_select_db("$DATABASE_DB",$dbh) or die("Unable to select database: ".mysql_error());
    return $dbconn;
  }
  
  function MakeInsertString ( $data ) {
    // Takes an associative array of $data and makes a string of fields and values like
    // (field1, field2, field3) VALUES ('value1', 'value2', 'value3')
    while ( list( $key, $val ) = each( $data ) ) {
      if ($key && $val) {
	$string["fields"] .= "$key, ";
	$string["values"] .= "'" . addslashes($val) . "', ";
      }
    }
    // Remove the last comma...
    $string["fields"]=preg_replace(", $","",$string["fields"]);
    $string["values"]=preg_replace(", $","",$string["values"]);
    
    // Return the completed string.
    return " ( $string[fields] ) VALUES $string[values] ";
  }
  
  function MakeUpdateString ($data) {
    // Similar to above, but instead makes a string of 
    while ( list( $key, $val ) = each( $data ) ) {
      if ($data[$key]) {
	$strings .= $key . " = '" . addslashes($val) . "', ";
      }
    }
    $strings=preg_replace(", $", " ", $strings);
    return $strings;
  }
  
  function dbQuery ($statement) {
    if (!isset($GLOBALS["CONNECTED_MYSQL_DB_INC"]))
      dbConnect();

    global $dbconn;

    $result=$dbconn->query($statement);
    $num_rows = dbNumRows($result);
    return array($result, $num_rows);
  }
  
  function tryDbQuery ($statement) {
    if (!isset($GLOBALS["CONNECTED_MYSQL_DB_INC"]))
      dbConnect();

    global $dbconn;

    $result=$dbconn->query($statement);
    $num_rows = dbNumRows($result);
    return array($result, $num_rows);  
  }
  
  function dbNumRows ($result) 
  {
    return @mysqli_num_rows($result);
  }
  
  function dbResult ($result,$i=-1) {
    if ($i >= 0) {
      @mysqli_data_seek($result,$i);
    }
    return mysqli_fetch_array($result);
  }
  
  function dbLastID($result) {
    return mysqli_insert_id($result);
  }

}?>
