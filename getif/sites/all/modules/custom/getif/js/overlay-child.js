(function ($) {

    // Adjust the overlay dimensions.
    Drupal.behaviors.getif = {

        attach: function (context) {
            $('#overlay:not(.getif-adjusted)', context).each(function() {
                var $test = $(this).find('.node-type-test');

                if ($test.length){
                    // adjust the overlay
                    $(this).css({
                        'width'     : '450px',
                        'min-width' : '450px'
                    });

                    $('.add-or-remove-shortcuts', this).hide();  // hide "add short-cut" button
                    $('#branding', this).hide();  // hide branding container
                }
            }).addClass('getif-adjusted');
        }

    };

})(jQuery);