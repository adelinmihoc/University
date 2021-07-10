import { NgModule } from '@angular/core';
import {RouterModule, Routes} from "@angular/router";
import {EntitiesComponent} from "./entities/entities.component";

const routes: Routes = [
  { path: 'entities', component:EntitiesComponent },
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule { }
