import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import {UsersComponent} from "../users/users.component";
import {RouterModule, Routes} from "@angular/router";
import {LoginComponent} from "../login/login.component";
import {RegisterComponent} from "../register/register.component";
import {UserAddComponent} from "../users/user-add/user-add.component";
import {UserDeleteComponent} from "../users/user-delete/user-delete.component";
import {UserUpdateComponent} from "../users/user-update/user-update.component";
import {UserListComponent} from "../users/user-list/user-list.component";
import {UserFilterComponent} from "../users/user-filter/user-filter.component";

const routes: Routes = [
  {path: 'users', component: UsersComponent},
  {path: 'login', component: LoginComponent},
  {path: 'register', component: RegisterComponent},
  {path: 'user-add', component: UserAddComponent},
  {path: 'user-delete', component: UserDeleteComponent},
  {path: 'user-update', component: UserUpdateComponent},
  {path: 'user-filter', component: UserFilterComponent}
]


@NgModule({
  declarations: [],
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule { }
