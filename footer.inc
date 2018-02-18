<?
	//Get the result set for the config set 1
  list($qhq, $numq) = dbQuery("select footerhtml from $CONFIG_TABLE where config_set_id = '1'");
  $configData = dbResult($qhq);
	parse_and_echo(stripslashes($configData["footerhtml"]));
?>
<p>
<table width="100%" class="grey_area">
	<tr>
		<td class="timesheet_logo">
			ACCOUNTMAN TIMESHEET
		</td>
		<td align="left">
			&copy; 2018 Desaur and co, <a href="http://www.desauandco.com">Desaur</a><br>
			&copy; 2018 Van
		</td>
		<td align="right">
			Usage under terms of <A HREF="http://www.desaurandco.com">All rights reserved</a>.
		</td>
	</tr>
</table>
