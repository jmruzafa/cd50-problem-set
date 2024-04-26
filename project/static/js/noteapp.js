$(function(){
	$('#company_copyright').append(new Date().getFullYear());
});
$('#delBtn').click(function(){
	return confirm("Are you sure?. This cannot be undone");
});