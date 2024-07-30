<?php
function node_edit_display_ctools_modal_exceptions_popup($js = FALSE) {
    ctools_include('modal');
    ctools_include('ajax');

// Create array $form_state.
    $title = ucfirst(arg(3));
    $form_state = array(
        'title' => t($title .' Action Role Exceptions'),
        'ajax'  => TRUE,
    );
    //add the action type, roleId, formId to the form state
    $form_state['build_info']['args'] = array(arg(3));
    $form_state['build_info']['args'][] = arg(5);
    $form_state['build_info']['args'][] = arg(6);
    $form_state['build_info']['args'][] = arg(7);
    $output = ctools_modal_form_wrapper('node_edit_display_ctools_modal_exceptions_form', $form_state);
    // Actions after form submit.
    if (!empty($form_state['executed'])) {
        $output = array();
        $value = _node_edit_display_get_role_exception_ids($form_state['values']['node_edit_display_action_role_exceptions']);
        _node_edit_display_set_role_exception_ids($form_state, $value);
        $id = 'node-edit-display-'.arg(3).'-exceptions-'. arg(5). '-'. arg(4);
        $input = '
';
        $input .= '';
        $input .= '
';
        $output[] = ajax_command_replace('#'.$id, $input);
        $output[] = ctools_modal_command_dismiss();
    }
    if (!$output) {
        $output = array();
        $output[] = ctools_modal_command_dismiss();
    }
    print ajax_render($output);
}