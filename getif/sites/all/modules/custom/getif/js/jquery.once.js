/*(function (global) {

    if(typeof (global) === "undefined") {
        throw new Error("window is undefined");
    }

    var _hash = "!";
    var noBackPlease = function () {
        global.location.href += "#";

        // making sure we have the fruit available for juice (^__^)
        global.setTimeout(function () {
            global.location.href += "!";
        }, 50);
    };

    global.onhashchange = function () {
        if (global.location.hash !== _hash) {
            global.location.hash = _hash;
        }
    };

    global.onload = function () {
        noBackPlease();

        // disables backspace on page except on input fields and textarea..
        document.body.onkeydown = function (e) {
            var elm = e.target.nodeName.toLowerCase();
            if (e.which === 8 && (elm !== 'input' && elm  !== 'textarea')) {
                e.preventDefault();
            }
            // stopping event bubbling up the DOM tree..
            e.stopPropagation();
        };
    }

})(window);
*/

jQuery(function($) {



    Drupal.behaviors.DisableInputEnter = {
        attach: function(context, settings) {
            $('input', context).once('disable-input-enter', function() {
                $(this).keypress(function(e) {
                    if (e.keyCode == 13) {
                        e.preventDefault();
                    }
                });
            });
        }
    }

    webshim.activeLang('it');
    webshims.setOptions('forms-ext', {
        types: 'number',
        replaceUI: true,
        lazyCustomMessages: true,
        replaceValidationUI: true,
		addValidators: true,
        "widgets": {
            "openOnFocus": true,
		}

    });
    webshim.ready('jquery', function(){
        webshim.loader.loadScript("../../demo-js/demo.js", false, false, true);
        webshim.loader.loadScript("assets/cfg.js", false, false, true);
    })
    // load the forms polyfill
    webshim.polyfill('forms forms-ext');











    // address
	$("#edit-address-city").bind('autocompleteSelect', function() {	
		var values = $(this).val().split('|');
		$(this).val(values[0]);
		if (values[1]) {
			$("#edit-address-zip-code").val(values[1]);
		}
	});

    // birthplace
    $("#edit-birthplace").bind('autocompleteSelect', function() {
        var values = $(this).val().split('|');
        $(this).val(values[0]);
        if (values[1]) {
            $("#edit-birthplace-zip-code").val(values[1]);
        }
    });
	
	
	
	$(".check_cp_primary").change(function() {
		if($(this).is(":checked")) {
            var returnVal = confirm("Sicuro di modificare la struttura primaria?");
            $(this).attr("checked", returnVal);
            var id = $(this).attr('id');
            $('.check_cp_primary').each(function (index, element ) {
    		    if($(element).attr('id') != id) {
    		    	$(element).attr('checked', false);	
    		    }
    		});
        }
		
    });

    $(".check_h_primary").change(function() {
        if($(this).is(":checked")) {
            var returnVal = confirm("Sicuro di modificare la struttura primaria?");
            $(this).attr("checked", returnVal);
            var id = $(this).attr('id');
            $('.check_h_primary').each(function (index, element ) {
                if($(element).attr('id') != id) {
                    $(element).attr('checked', false);
                }
            });
        }

    });
	
	
	
	$("#edit-intern").bind('autocompleteSelect', function() {	
		var values = $(this).val().split('|');
		$(this).val(values[0]);
		if (values[1]) {
			$("#edit-intern_id").val(values[1]);
		}
	
	});
	
	
	$("#edit-promoter").bind('autocompleteSelect', function() {
		var values = $(this).val().split('|');
		$(this).val(values[0]);
		if (values[1]) {
			$("#promoter_id").val(values[1]);
		}
	
	});	
	/*$("#edit-promoter").bind('blur', function() {
		
		var values = $(this).val().split('|');

		$(this).val(values[0]);
		if (values[1]) {
			$("#promoter_id").val(values[1]);
		}
	
	});*/
	$("#edit-host").bind('autocompleteSelect', function() {
		var values = $(this).val().split('|');
		$(this).val(values[0]);
		if (values[1]) {
			$("#host_id").val(values[1]);
		}
	});
	/*$("#edit-host").bind('blur', function() {
		
		var values = $(this).val().split('|');
		$(this).val(values[0]);
		if (values[1]) {
			$("#edit-host").val(values[1]);
		}
	
	});*/
	
	
	
	
	// tirocinio new 3
	$("#edit-host-tutor").bind('autocompleteSelect', function() {	
		var values = $(this).val().split('|');
		$(this).val(values[0]);
		if (values[1]) {
			$("#edit-host-tutor_id").val(values[1]);
		}
	});
	$("#edit-promoter-tutor").bind('autocompleteSelect', function() {
		
		var values = $(this).val().split('|');
		$(this).val(values[0]);
		if (values[1]) {
			$("#edit-promoter-tutor_id").val(values[1]);
		}
	});
	$("#edit-cperson").bind('autocompleteSelect', function() {
		
		var values = $(this).val().split('|');
		$(this).val(values[0]);
		if (values[1]) {
			$("#edit-cperson_id").val(values[1]);
		}
	
	});
	$("#edit-location").bind('autocompleteSelect', function() {
		
		var values = $(this).val().split('|');
		$(this).val(values[0]);
		if (values[1]) {
			$("#edit-location_id").val(values[1]);
		}
	
	});
	
	$("#edit-person").bind('autocompleteSelect', function() {
		
		var values = $(this).val().split('|');
		$(this).val(values[0]);
		if (values[1]) {
			$("#edit-person-id").val(values[1]);
		}
	
	});


    $('.js-date').mask('99-99-9999',{placeholder:"gg-mm-aaaa"});






    $('.mask_time').mask('00:00');
});





