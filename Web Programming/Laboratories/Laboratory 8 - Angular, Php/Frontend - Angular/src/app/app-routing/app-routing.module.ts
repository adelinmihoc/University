import { NgModule } from '@angular/core';
import {RouterModule, Routes} from '@angular/router';
import {UsersComponent} from '../users/users.component';
import {UserAddComponent} from '../users/user-add/user-add.component';
import {UserDeleteComponent} from '../users/user-delete/user-delete.component';
import {UserUpdateComponent} from '../users/user-update/user-update.component';
import {UserLookupComponent} from '../users/user-lookup/user-lookup.component';
import {UserBrowseComponent} from '../users/user-browse/user-browse.component';

const routes: Routes = [
  {path: 'users', component: UsersComponent},
  {path: 'user-add', component: UserAddComponent},
  {path: 'user-delete', component: UserDeleteComponent},
  {path: 'user-update', component: UserUpdateComponent},
  {path: 'user-lookup', component: UserLookupComponent},
  {path: 'user-browse', component: UserBrowseComponent}
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule { }
