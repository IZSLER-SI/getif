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
    /* Datatables */
    if ($.fn.dataTableExt) {
        $.extend($.fn.dataTableExt.oSort, {
            "date-eu-pre": function (date) {
                date = date.replace(" ", "");
                if (!date) {
                    return 0;
                }

                var year;
                var eu_date = date.split(/[\.\-\/]/);

                /*year (optional)*/
                if (eu_date[2]) {
                    year = eu_date[2];
                }
                else {
                    year = 0;
                }

                /*month*/
                var month = eu_date[1];
                if (month.length == 1) {
                    month = 0 + month;
                }

                /*day*/
                var day = eu_date[0];
                if (day.length == 1) {
                    day = 0 + day;
                }

                return (year + month + day) * 1;
            },

            "date-eu-asc": function (a, b) {
                return ((a < b) ? -1 : ((a > b) ? 1 : 0));
            },

            "date-eu-desc": function (a, b) {
                return ((a < b) ? 1 : ((a > b) ? -1 : 0));
            }
        });
    }
    /* end */

    /** Disattiva il tasto ENTER per inviare il form **/
    /*Drupal.behaviors.DisableInputEnter = {
        attach: function(context, settings) {
            $('input', context).once('disable-input-enter', function() {
                $(this).keypress(function(e) {
                    if (e.keyCode == 13) {
                        e.preventDefault();
                    }
                });
            });
        }
    }*/

    /* Gestione date */
    var dateFormat = "dd-mm-yy",
        date = $( "input.date-popup-init[name*='[date]']" )
            .datepicker({
                defaultDate: "+1w",
                changeMonth: true,
                dateFormat: "dd-mm-yy",
                numberOfMonths: 1
            })
            .on( "change", function() {
                var value = date.datepicker({ dateFormat: dateFormat }).val();
                if (isValidDate(value)) {
                    date.val(value);
                } else {
                    date.val("");
                }
            }),
        appl = $( "input[range*='date_application']"  )
            .datepicker({
                defaultDate: "+1w",
                changeMonth: true,
                changeYear: true,
                dateFormat: "dd-mm-yy",
                numberOfMonths: 1
            })
            .on( "change", function() {
                var value = appl.datepicker({ dateFormat: dateFormat }).val();
                if (isValidDate(value)) {
                    appl.val(value);
                    from.datepicker( "option", "minDate", getDate( this ));
                } else {
                    appl.val("");
                }
            }),
        from = $( "input[range*='date_start']" )
            .datepicker({
                defaultDate: "+1w",
                changeMonth: true,
                changeYear: true,
                dateFormat: "dd-mm-yy",
                numberOfMonths: 1
            })
            .on( "change", function() {
                var value = from.datepicker({ dateFormat: dateFormat }).val();
                if (isValidDate(value)) {
                    from.val(value);
                    appl.datepicker( "option", "maxDate", getDate( this ) );
                    to.datepicker( "option", "minDate", getDate( this ) );
                    if (to.attr('maxDuration')) {
                        to.datepicker( "option", "maxDate", add_months(getDate(this), parseInt(to.attr('maxDuration'))));
                    }
                } else {
                    from.val("");
                }
            }),
        to = $( "input[range*='date_end']" )
            .datepicker({
                defaultDate: "+1w",
                changeMonth: true,
                changeYear: true,
                dateFormat: "dd-mm-yy",
                numberOfMonths: 1,

            })
            .ready(function(){
                var value = to.datepicker({dateFormat: dateFormat}).val();
                if (isValidDate(value)) {
                    to.val(value);
                    var value_from = from.datepicker({dateFormat: dateFormat}).val();
                    to.datepicker("option", "minDate", getDate({value: value_from}));
                }
            })
            .on( "change", function() {
                var value = to.datepicker({ dateFormat: dateFormat }).val();
                if (isValidDate(value)) {
                    to.val(value);
                    from.datepicker( "option", "maxDate", getDate( this ) );
                } else {
                    to.val("");
                }
            }),

        filter_from = $( "input[range*='filter_date_start']" )
            .datepicker({
                defaultDate: "+1w",
                changeMonth: true,
                changeYear: true,
                dateFormat: "dd-mm-yy",
                numberOfMonths: 1,

            })
            .each(function() {
                if (typeof $(this).attr('minDate') != "undefined") {
                    $(this).datepicker( "option", "minDate", getDate({value: $(this).attr('minDate')}) );
                }
                if (typeof $(this).attr('maxDate') != "undefined") {
                    $(this).datepicker( "option", "maxDate", getDate({value: $(this).attr('maxDate')}) );
                }
            })
            .on( "change", function() {
                var value = filter_from.datepicker({ dateFormat: dateFormat }).val();
                if (isValidDate(value)) {
                    filter_from.val(value);
                    filter_to.datepicker( "option", "minDate", getDate( this ) );
                    if (filter_to.attr('maxDuration')) {
                        filter_to.datepicker( "option", "maxDate", add_months(getDate(this), parseInt(to.attr('maxDuration'))));
                    }
                } else {
                    filter_from.val("");
                }
            }),
        filter_to = $( "input[range*='filter_date_end']" )
            .datepicker({
                defaultDate: "+1w",
                changeMonth: true,
                changeYear: true,
                dateFormat: "dd-mm-yy",
                numberOfMonths: 1,

            })
            .each(function() {
                if (typeof $(this).attr('maxDate') != "undefined") {
                    $(this).datepicker( "option", "maxDate", getDate({value: $(this).attr('maxDate')}) );
                }
            })
            .ready(function(){
                var value = filter_to.datepicker({dateFormat: dateFormat}).val();
                if (isValidDate(value)) {
                    filter_to.val(value);
                    var value_from = filter_from.datepicker({dateFormat: dateFormat}).val();
                    filter_to.datepicker("option", "minDate", getDate({value: value_from}));
                }
            })
            .on( "change", function() {
                var value = filter_to.datepicker({ dateFormat: dateFormat }).val();
                if (isValidDate(value)) {
                    filter_to.val(value);
                    filter_from.datepicker( "option", "maxDate", getDate( this ) );
                } else {
                    filter_to.val("");
                }
            });





    function add_months(dt, n)
    {

        return new Date(dt.setMonth(dt.getMonth() + n));
    }

    function getDate( element ) {
        var date;
        try {
            date = $.datepicker.parseDate( dateFormat, element.value );
            //alert(element.value);
        } catch( error ) {
            date = null;
        }

        return date;
    }

    function isValidDate(s) {
        if (typeof s !== 'undefined') {
            var bits = s.split('-');
            var d = new Date(bits[2] + '-' + bits[1] + '-' + bits[0]);
            return !!(d && (d.getMonth() + 1) == bits[1] && d.getDate() == Number(bits[0]));
        } else {
            return false;
        }
    }

    function daysInMonth(month, year) {
        return new Date(year, month, 0).getDate();
    }


    /*

    // Helper function to add an event listener
    function addEvent (el, event, callback) {
        if ('addEventListener' in el) {                  // If addEventListener works
            el.addEventListener(event, callback, false);   // Use it
        } else {                                         // Otherwise
            el['e' + event + callback] = callback;         // CreateIE fallback
            el[event + callback] = function () {
                el['e' + event + callback](window.event);
            };
            el.attachEvent('on' + event, el[event + callback]);
        }
    }

    // Helper function to remove an event listener
    function removeEvent(el, event, callback) {
        if ('removeEventListener' in el) {                      // If removeEventListener works
            el.removeEventListener(event, callback, false);       // Use it
        } else {                                                // Otherwise
            el.detachEvent('on' + event, el[event + callback]);   // Create IE fallback
            el[event + callback] = null;
            el['e' + event + callback] = null;
        }
    }




    (function() {

        var pwd = document.getElementById('edit-pass-fields-pass1');     // Get password input
        var chk = document.getElementById('edit-pass-show'); // Get checkbox

        if(pwd !== null) {
            addEvent(chk, 'change', function (e) {         // When user clicks on checkbox
                var target = e.target || e.srcElement;      // Get that element
                try {                                       // Try the following code block
                    if (target.checked) {                     // If the checkbox is checked
                        pwd.type = 'text';                      // Set pwd type to text
                    } else {                                  // Otherwise
                        pwd.type = 'password';                  // Set pwd type to password
                    }
                } catch (error) {                            // If this causes an error
                    alert('This browser cannot switch type'); // Say that cannot switch type
                }
            });
        }

    }());
    */
    // Formato numeri e date
    //console.log(webshim);
    if (typeof webshim !== 'undefined') {

        webshim.setOptions('forms', {
            lazyCustomMessages: true,
            replaceValidationUI: true,
            addValidators: true
        });
        webshim.activeLang('it'); //set locale to it
        webshims.validityMessages.en = {
            "typeMismatch": {
                "defaultMessage": "Please enter a valid value.",
                "email": "Please enter an email address.",
                "url": "Please enter a URL."
            },
            "badInput": {
                "defaultMessage": "Please enter a valid value.",
                "number": "Please enter a number.",
                "date": "Please enter a date.",
                "time": "Please enter a time.",
                "range": "Invalid input.",
                "month": "Please enter a valid value.",
                "datetime-local": "Please enter a datetime."
            },
            "rangeUnderflow": {
                "defaultMessage": "Value must be greater than or equal to {%min}.",
                "date": "Value must be at or after {%min}.",
                "time": "Value must be at or after {%min}.",
                "datetime-local": "Value must be at or after {%min}.",
                "month": "Value must be at or after {%min}."
            },
            "rangeOverflow": {
                "defaultMessage": "Value must be less than or equal to {%max}.",
                "date": "Value must be at or before {%max}.",
                "time": "Value must be at or before {%max}.",
                "datetime-local": "Value must be at or before {%max}.",
                "month": "Value must be at or before {%max}."
            },
            "stepMismatch": "Invalid input.",
            "tooLong": "Please enter at most {%maxlength} character(s). You entered {%valueLen}.",
            "tooShort": "Please enter at least {%minlength} character(s). You entered {%valueLen}.",
            "patternMismatch": "Invalid input. {%title}",
            "valueMissing": {
                "defaultMessage": "Please fill out this field.",
                "checkbox": "Please check this box if you want to proceed.",
                "select": "Please select an option.",
                "radio": "Please select an option."
            }
        };
        webshims.formcfg.it = {
            "numberFormat": {
                ".": ",",
                ",": "."
            },
            "numberSigns": ",",
            "dateSigns": "-",
            "timeSigns": ":. ",
            "dFormat": "-",
            "patterns": {
                "d": "yy-mm-dd"
            },
            "month": {
                "currentText": "Questo mese"
            },
            "time": {
                "currentText": "Adesso"
            },
            "date": {
                "closeText": "Fatto",
                "clear": "Pulisci",
                "prevText": "Precedente",
                "nextText": "Successivo",
                "currentText": "Oggi",
                "monthNames": [
                    "Gennaio",
                    "Febbraio",
                    "Marzo",
                    "Aprile",
                    "Maggio",
                    "Giugno",
                    "Luglio",
                    "Agosto",
                    "Settembre",
                    "Ottobre",
                    "Novembre",
                    "Dicembre"
                ],
                "monthNamesShort": [
                    "Gen",
                    "Feb",
                    "Mar",
                    "Apr",
                    "Mag",
                    "Giu",
                    "Lug",
                    "Ago",
                    "Set",
                    "Ott",
                    "Nov",
                    "Dic"
                ],
                "dayNames": [
                    "Domenica",
                    "Lunedì",
                    "Martedì",
                    "Mercoledì",
                    "Giovedì",
                    "Venerdì",
                    "Sabato"
                ],
                "dayNamesShort": [
                    "Dom",
                    "Lun",
                    "Mar",
                    "Mer",
                    "Gio",
                    "Ven",
                    "Sab"
                ],
                "dayNamesMin": [
                    "Do",
                    "Lu",
                    "Ma",
                    "Me",
                    "Gi",
                    "Ve",
                    "Sa"
                ],
                "weekHeader": "Wk",
                "firstDay": 1,
                "isRTL": false,
                "showMonthAfterYear": false,
                "yearSuffix": ""
            }
        };
        webshims.setOptions('forms-ext', {
            replaceUI: true,
            "number": {
                "classes": "inputbtns"
            },
            "date": {
                "openOnFocus": true,
            }
        });
        // load the forms polyfill
        webshim.polyfill('forms forms-ext');
    }


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
                    $(element).removeAttribute('checked');
                }
            });
        } else {
        }
    });

    var intern_select = false;
    $("#edit-intern").bind('autocompleteSelect', function() {
        var values = $(this).val().split('|');
        $(this).val(values[0]);
        if (values[1]) {
            $("#edit-intern_id").val(values[1]);
            intern_select = true;
        }
    }).blur(function() {
        if(intern_select == false) {
            $("#edit-intern").val("");
        }
        intern_select = false;
    });





    var promoter_select = false;
    $("#edit-promoter").bind('autocompleteSelect', function() {
        var values = $(this).val().split('|');
        $(this).val(values[0]);
        if (values[1]) {
            $("#promoter_id").val(values[1]);
            promoter_select = true;
        }
    }).blur(function() {
        if(promoter_select == false) {
            $("#edit-promoter").val("");
        }
        promoter_select = false;
    });
    /*$("#edit-promoter").bind('blur', function() {

        var values = $(this).val().split('|');

        $(this).val(values[0]);
        if (values[1]) {
            $("#promoter_id").val(values[1]);
        }

    });*/
    var host_select = false;
    $("#edit-host").bind('autocompleteSelect', function() {
        var values = $(this).val().split('|');
        $(this).val(values[0]);
        if (values[1]) {
            $("#host_id").val(values[1]);
            host_select = true;
        }
    }).blur(function() {
        if(host_select == false) {
            $("#edit-host").val("");
        }
        host_select = false;
    });
    /*$("#edit-host").bind('blur', function() {

        var values = $(this).val().split('|');
        $(this).val(values[0]);
        if (values[1]) {
            $("#edit-host").val(values[1]);
        }

    });*/


    var host_tutor_select = false;
    $("#edit-host-tutor").bind('autocompleteSelect', function() {
        var values = $(this).val().split('|');
        $(this).val(values[0]);
        if (values[1]) {
            $("#edit-host-tutor_id").val(values[1]);
            host_tutor_select = true;
        }
    }).blur(function() {
        if(host_tutor_select == false) {
            $("#edit-host-tutor").val("");
        }
        host_tutor_select = false;
    });

    var promoter_tutor_select = false;
    $("#edit-promoter-tutor").bind('autocompleteSelect', function() {
        var values = $(this).val().split('|');
        $(this).val(values[0]);
        if (values[1]) {
            $("#edit-promoter-tutor_id").val(values[1]);
            promoter_tutor_select = true;
        }
    }).blur(function() {
        if(promoter_tutor_select == false) {
            $("#edit-promoter-tutor").val("");
        }
        promoter_tutor_select = false;
    });


    var cperson_select = false;
    $("#edit-cperson").bind('autocompleteSelect', function() {
        var values = $(this).val().split('|');
        $(this).val(values[0]);
        if (values[1]) {
            $("#edit-cperson_id").val(values[1]);
            cperson_select = true;
        }

    }).blur(function() {
        if(cperson_select == false) {
            $("#edit-cperson").val("");
        }
        cperson_select = false;
    });

    var location_select = false;
    $("#edit-location").bind('autocompleteSelect', function() {

        var values = $(this).val().split('|');
        $(this).val(values[0]);
        if (values[1]) {
            $("#edit-location_id").val(values[1]);
            location_select = true;
        }

    }).blur(function() {
        if(location_select == false) {
            $("#edit-location").val("");
        }
        location_select = false;
    });

    var person_select = false;
    $("#edit-person").bind('autocompleteSelect', function() {

        var values = $(this).val().split('|');
        $(this).val(values[0]);
        if (values[1]) {
            $("#edit-person-id").val(values[1]);
            person_select = true;
        }

    }).blur(function() {
        if(person_select == false) {
            $("#edit-person").val("");
        }
        person_select = false;
    });


    /*var agreeement_select = false;
    $("#edit-agreement").bind('autocompleteSelect', function() {

        var values = $(this).val().split('|');
        $(this).val(values[0]);
        if (values[1]) {
            $("#edit-agreement_id").val(values[1]);
            agreeement_select = true;
        }

    }).blur(function() {
        if(agreeement_select == false) {
            $("#edit-agreement").val("");
        }
        agreeement_select = false;
    });*/

    var internship_select = false;
    $("#edit-internship").bind('autocompleteSelect', function() {

        var values = $(this).val().split('|');
        $(this).val(values[0]);
        if (values[1]) {
            $("#edit-internship_id").val(values[1]);
            internship_select = true;
        }

    }).blur(function() {
        if(internship_select == false) {
            $("#edit-internship").val("");
        }
        internship_select = false;
    });

    $("#edit-internship").mousedown(function() {
        $("#edit-internship").val("");
        $("#edit-internship_id").val("");
    });

    $("#edit-agreement").mousedown(function() {
        $("#edit-agreeement").val("");
        $("#edit-agreeemnt_id").val("");
    });

    $("#edit-add-name").mousedown(function() {
        $("#edit-location").val("");
        $("#edit-location_id").val("");
    });

    $("#edit-add-location").mousedown(function() {
        $("#edit-location").val("");
        $("#edit-location_id").val("");
    });

    $("#edit-add-promoter-tutor").mousedown(function() {
        $("#edit-promoter-tutor").val("");
        $("#edit-promoter-tutor_id").val("");
    });

    $("#edit-add-host-tutor").mousedown(function() {
        $("#edit-host-tutor").val("");
        $("#edit-host-tutor_id").val("");
    });

    $("#edit-add-cperson").mousedown(function() {
        $("#edit-cperson").val("");
        $("#edit-host-cperson_id").val("");
    });
    $("#edit-add-person").mousedown(function() {
        $("#edit-person").val("");
        $("#edit-person-id").val("");
    });
    $("#edit-add-lperson-location-area").mousedown(function() {
        $("#edit-lperson-location-area-name").val("");
        $("#edit-person-id").val("");
    });

    $('.js-date').mask('99-99-9999',{placeholder:"gg-mm-aaaa"});
    $('.mask_time').mask('00:00');
});