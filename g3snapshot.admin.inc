<?php

/**
 * Settings form
 */
function g3snapshot_settings_form() {

  $form = array();

  $months = range(1, 12);
  $form['g3snapshot_show_limit_container'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('container-inline')),
    'g3snapshot_show_limit' => array(
      '#type' => 'select',
      '#options' => array_combine($months, $months),
      '#default_value' => variable_get('g3snapshot_show_limit', 12),
      '#prefix' => 'Show the newest snapshots from up to ',
      '#suffix' => 'month(s)',
    ),
  );

  // WOW this is a bad idea. Module needs knowledge of all possible other modules

  if( module_exists('ga_community') ) {
    $form['g3snapshot_opportunities'] = array(
      '#type' => 'checkbox',
      '#title' => 'Enable snapshots for opportunities',
      '#default_value' => variable_get('g3snapshot_opportunities', FALSE),
      '#description' => "Check this box to take data snapshots of opportunities when cron is run",
    );
  }

  $form = system_settings_form($form);

  return $form;
}
