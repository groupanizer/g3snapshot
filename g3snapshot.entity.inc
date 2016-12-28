<?php

/**
 * Implements hook_entity_info().
 */
function g3snapshot_entity_info() {

  $entity_info['g3snapshot'] = array(
    'label' => t('Snapshot'),
    'plural label' => t('Snapshots'),
    'label callback' => 'entity_class_label',
    'uri callback' => 'entity_class_uri',
    'description' => t('A record of data taken at a specified month and year'),
    'base table' => 'g3snapshot',
    'entity keys' => array(
      'id' => 'sid',
    ),
    'module' => 'g3snapshot',
    'entity class' => 'SnapshotEntity',
    'controller class' => 'SnapshotAPIController',
    'access callback' => 'g3snapshot_access_callback',

    'fieldable' => TRUE,
    'views controller class' => 'EntityDefaultViewsController',
  );

  return $entity_info;
}

/**
 * Snapshot entity
 */

class SnapshotEntity extends Entity {


  protected function defaultLabel() {
    return $this->label;
  }

}

class SnapshotAPIController extends EntityAPIController {

  public function load($ids = array(), $conditions = array()) {
    $entities = parent::load($ids, $conditions);
    return $entities;
  }

  protected function attachLoad(&$entities, $revision_id = FALSE) {
    parent::attachLoad($entities, $revision_id);
    $ids = array_keys($entities);

    // load data
    $data = db_query(
     "SELECT * FROM g3snapshot_data WHERE sid IN(:ids)",
      array(':ids'=>$ids))->fetchAll();

    foreach($data AS $d) {
      $entities[$d->sid]->data[$d->type] = $d->data;
    }

  }

  public function save($entity) {
    parent::save($entity);
  }

  public function delete($ids, DatabaseTransaction $transaction = NULL) {
    parent::delete($ids, $transaction);
  }

}

function g3snapshot_access_callback($op, $g3snapshot = NULL, $account = NULL) {
  return FALSE;
}

/**
 * hook_load
 */
function g3snapshot_load($id = null, $reset = FALSE) {
  return entity_load_single('g3snapshot', $id, $reset);
}


function g3snapshot_view($g3snapshot) {
  return MENU_NOT_FOUND;
}
