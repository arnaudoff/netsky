import { Routes } from '@angular/router';

import { HomeRoutes } from './home/index';
import { CaptureRoutes } from './capture/index';

export const routes: Routes = [
  ...HomeRoutes,
  ...CaptureRoutes,
  { path: '', redirectTo: 'home', pathMatch: 'full' }
];
