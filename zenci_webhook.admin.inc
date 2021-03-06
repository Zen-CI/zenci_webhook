<?php

/**
 * @file
 * Admin settings menu callbacks for ZenCI webhooks.
 */

/**
 * Adding a module settings to work with Github.
 */
function zenci_webhook_admin_settings($form, &$form_state) {
  $config = config('zenci_webhook.settings');

  // Use setting.php values if exists.
  $api_token = settings_get('zenci_webhook_api_token');

  $form['api_token'] = array(
    '#type' => 'textfield',
    '#title' => t('zenci webhook API token'),
    '#default_value' => !empty($api_token) ? $api_token : $config->get('api_token'),
    '#description' => t('You can obtain API Key on http://git.lc/api/settings page'),
    '#disabled' => !empty($api_token) ? TRUE : FALSE,
  );
  $form['actions']['#type'] = 'actions';
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save API'),
  );
  return $form;
}

/**
 * Submit handler for the webhook_admin_settings() form.
 */
function zenci_webhook_admin_settings_submit($form, &$form_state) {
  $config = config('zenci_webhook.settings');

  $api_token = settings_get('zenci_webhook_api_token');
  if (empty($api_token)) {
    $config->set('api_token', $form_state['values']['api_token']);
  }
  $config->save();
  backdrop_set_message(t('The configuration options have been saved.'));
}
