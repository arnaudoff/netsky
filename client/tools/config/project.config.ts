import { join } from 'path';

import { SeedConfig } from './seed.config';
import { ExtendPackages } from './seed.config.interfaces';

/**
 * This class extends the basic seed configuration,
 * allowing for project specific overrides. A few examples can be found
 * below.
 */
export class ProjectConfig extends SeedConfig {

  PROJECT_TASKS_DIR = join(process.cwd(), this.TOOLS_DIR, 'tasks', 'project');

  FONTS_DEST = `${this.APP_DEST}/css/themes/default/assets/fonts/`;
  FONTS_SRC = [
      'node_modules/semantic-ui-css/themes/default/assets/fonts/**'
  ];

  constructor() {
    super();
    this.APP_TITLE = 'Netsky';

    /* Enable typeless compiler runs (faster) between typed compiler runs. */
    // this.TYPED_COMPILE_INTERVAL = 5;

    // Add `NPM` third-party libraries to be injected/bundled.
    this.NPM_DEPENDENCIES = [
      ...this.NPM_DEPENDENCIES,
      { src: 'jquery/dist/jquery.min.js', inject: 'libs'},
      { src: 'semantic-ui-css/semantic.min.js', inject: 'libs'},
      { src: 'semantic-ui-css/semantic.min.css', inject: true},
      { src: 'searchjs/lib/searchjs.js', inject: 'libs'}
    ];

    // Add `local` third-party libraries to be injected/bundled.
    this.APP_ASSETS = [
      ...this.APP_ASSETS,
    ];

    let additionalPackages: ExtendPackages[] = [{
      name: 'd3',
      path: 'node_modules/d3/d3.min.js'
    },
    {
      name: 'angular2-virtual-scroll',
      path: 'node_modules/angular2-virtual-scroll/dist/virtual-scroll.js'
    }];

    this.addPackagesBundles(additionalPackages);

    /* Add to or override NPM module configurations: */
    // this.mergeObject(this.PLUGIN_CONFIGS['browser-sync'], { ghostMode: false });
  }

}
