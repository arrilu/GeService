function merciHandleTaxonomyPost( json )
{

	var response = eval( '(' + json + ')' )
	
	if ( response.error )
	{
	
	} // if
	else
	{
	
		merciSendingTaxonomy[ response.node ] = false
	
		$.get( '/merci/taxonomy/' + response.node , {} , merciHandleTaxonomyJSON )
	
	} // else	

} // merciHandleTaxonomyPost

function merciHandleTaxonomyJSON( json )
{

	var response = eval( '(' + json + ')' )
	var edit = $( '#merci-id-' + response.node ).find( 'a' )

	edit.parent().find( '.complete' ).remove()

	if ( response.error )
	{

	} // if
	else
	{

		edit.data( 'info' , response )

		var done = false

		for ( var vocabularyId in response.vocabularies )
		{

			var vocabulary = response.vocabularies[ vocabularyId ]

			if ( vocabulary.selected.length > 0 ) done = true

		} // for

		if ( done )
		{

			var checkMark = $( '<span class="complete"> &#10003;</span>' )

			if ( response.admin ) checkMark.addClass( 'admin' )

			checkMark.insertAfter( edit )

		} // if
		else
		{

		} // else

		edit.click(

			function()
			{

				var $this = $( this )
				var offset = $this.offset()
				var info = $this.data( 'info' )

				$( '#merci-taxonomy-edit' ).remove()

				var div = $( '<div id="merci-taxonomy-edit"></div>' )
					.css(
						{
							'background' : '#fff' ,
							'border' : '1px #999 solid' ,
							'padding' : '1em' ,
							'position' : 'absolute' ,
							'top' : offset.top + 20 ,
							'left' : offset.left
						}
					)
					.click( function(){ return false } )

				for ( var vocabularyId in info.vocabularies )
				{

					var vocabulary = info.vocabularies[ vocabularyId ]
					var select = $( vocabulary.select )

					for ( var selectedId in vocabulary.selected )
					{

						var termId = vocabulary.selected[ selectedId ]

						select.find( 'option[value=' + termId + ']' ).attr( 'selected' , true )

					} // for

					div.append( select )

				} // for

				$( '<input type="button" value="Save" />' )
					.click( merciSaveTaxonomy )
					.appendTo( div )

				div
					.appendTo( 'body' )
					.data( 'node' , info.node )

				return false

			} // function

		) // $.click

	} // else

} // merciHandleTaxonomyJSON

function merciSaveTaxonomy()
{

	var parameters = {}
	var selectionId = 0
	var nodeId = $( '#merci-taxonomy-edit' ).data( 'node' )
	
	if ( ! merciSendingTaxonomy[ nodeId ] )
	{
	
		merciSendingTaxonomy[ nodeId ] = true
	
		$( '#merci-taxonomy-edit select option:selected' ).each(
	
			function()
			{
	
				var $this = $( this )
				var select = $this.parent( 'select' )
				var name = select.attr( 'name' )
	
				parameters[ name.slice( 0 , name.length - 1 ) + selectionId + ']' ] = $this.attr( 'value' )
	
				selectionId++
	
			} // function
	
		) // $.each
	
		$.post( '/merci/taxonomy/' + nodeId , parameters , merciHandleTaxonomyPost )

	} // if

	$( '#merci-taxonomy-edit' ).remove()
	

} // merciSaveTaxonomy

$( document ).ready(

	function()
	{

		$( 'body' ).click(

			function()
			{

				$( '#merci-taxonomy-edit' ).remove()

			} // function

		) // $.click

		$( 'span.edit-details' ).each(

			function()
			{

				var $this = $( this )
				var nodeId = $this.attr( 'id' ).split( '-' )[2]

				$.get( '/merci/taxonomy/' + nodeId , {} , merciHandleTaxonomyJSON )

			} // function

		) // $.each

	} // function

) // $.ready

var merciSendingTaxonomy = []