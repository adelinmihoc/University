import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';
import {ParentsComponent} from "./parents/parents.component";
import {ParentAddComponent} from "./parents/parent-add/parent-add.component";
import {ParentDeleteComponent} from "./parents/parent-delete/parent-delete.component";
import {ParentUpdateComponent} from "./parents/parent-update/parent-update.component";
import {RegisterComponent} from "./authentication/register/register.component";
import {LoginComponent} from "./authentication/login/login.component";
import {LogoutComponent} from "./authentication/logout/logout.component";
import {FilterDestinationsComponent} from "./parents/filter-destinations/filter-destinations.component";

const routes: Routes = [
  {path: 'parents', component:ParentsComponent},
  {path: 'parent-add', component:ParentAddComponent},
  {path: 'parent-delete', component:ParentDeleteComponent},
  {path: 'parent-update', component:ParentUpdateComponent},
  {path: 'register', component:RegisterComponent},
  {path: 'login', component:LoginComponent},
  {path: 'logout', component:LogoutComponent},
  {path: 'filter', component:FilterDestinationsComponent},
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule { }
